#include "ownCmds.hpp"
#include <set>

void skuratov::help(std::ostream& out)
{
  out << "  load <text1> <text1.txt> - �������� ���������������� ������ �� �����\n";
  out << "  huff <codes1> <text1> - �������� ��������� ��� �� �������������� ������\n";
  out << "  compress <encoded1> <text1> <codes1> - ������ ������\n";
  out << "  save <encoded1> <output1.bin> - ���������� ������\n";
  out << "  load_encoded <text3> <codes1> <output1.bin> - �������� �������������� ������ �� �����\n";
  out << "  decompress <decoded1> <text3> <codes1> -  �������������� ������� �����\n";
  out << "  eff text1 codes1 - ����� ������������� ������ ������\n";
  out << "  sort_data <encoded1> - ���������� ������\n";
  out << "  remove_duplicates <text1> - �������� ������������� ���� �� ������\n";
  out << "  count_words <text1> - ������� ���������� ���� � ������\n";
}

void skuratov::load(std::istream& in, std::ostream& out, Context& context)
{
  std::string textVar, infile;

  in >> textVar >> infile;

  std::ifstream file(infile);
  if (!file)
  {
    out << "<INVALID LOAD>" << '\n';
    return;
  }

  std::string text((std::istreambuf_iterator< char >(file)), std::istreambuf_iterator< char >());
  context.context[textVar] = text;
}

void skuratov::huff(std::istream& in, std::ostream& out, Context& context, CodeContext& codeContext)
{
  std::string codesVar, textVar;
  in >> codesVar >> textVar;

  if (context.context.find(textVar) == context.context.end())
  {
    out << "<INVALID HUFF>" << '\n';
    return;
  }

  std::string text = context.context[textVar];
  std::map< char, std::string > huffmanCodes;

  try
  {
    createHuffmanCodes(text, huffmanCodes);
    codeContext.codeContext[codesVar] = huffmanCodes;
  }
  catch (...)
  {
    out << "<INVALID HUFF>" << '\n';
  }
}

void skuratov::compress(std::istream& in, std::ostream& out, Context& context, CodeContext& codeContext)
{
  std::string encodedVar, textVar, codesVar;
  in >> encodedVar >> textVar >> codesVar;

  if (context.context.find(textVar) == context.context.end() || codeContext.codeContext.find(codesVar) == codeContext.codeContext.end())
  {
    out << "<INVALID COMPRESSION>" << '\n';
    return;
  }

  std::string text = context.context[textVar];
  std::map< char, std::string > huffmanCodes = codeContext.codeContext[codesVar];
  std::string encodedText;

  if (compressText(text, huffmanCodes, encodedText))
  {
    context.context[encodedVar] = encodedText;
    out << "Text compressed into " << encodedVar << "\n";
  }
  else
  {
    out << "<INVALID COMPRESSION>" << '\n';
  }
}

void skuratov::save(std::istream& in, std::ostream& out, const Context& context)
{
  std::string encodedVar, outputFile;
  in >> encodedVar >> outputFile;

  auto it = context.context.find(encodedVar);
  if (it == context.context.end())
  {
    out << "<INVALID SAVE>" << '\n';
    return;
  }

  std::ofstream outfile(outputFile, std::ios::binary);
  if (!outfile)
  {
    out << "<INVALID SAVE>" << '\n';
    return;
  }

  outfile << it->second;
  out << "Data saved to " << outputFile << "\n";
}

void skuratov::loadEncoded(std::istream& in, std::ostream& out, CodeContext& codeContext)
{
  std::string codesVar, filename;
  in >> codesVar >> filename;

  std::ifstream infile(filename);
  if (!infile)
  {
    out << "<INVALID LOAD ENCODED>" << '\n';
    return;
  }

  std::map< char, std::string > huffmanCodes;
  char ch = {};
  std::string code;
  while (infile >> ch >> code)
  {
    huffmanCodes[ch] = code;
  }

  codeContext.codeContext[codesVar] = huffmanCodes;
}

void skuratov::decompress(std::istream& in, std::ostream& out, Context& context, CodeContext& codeContext)
{
  std::string decodedVar, encodedVar, codesVar;
  in >> decodedVar >> encodedVar >> codesVar;

  if (context.context.find(encodedVar) == context.context.end() || codeContext.codeContext.find(codesVar) == codeContext.codeContext.end())
  {
    out << "<INVALID DECOMPRESSION>" << '\n';
    return;
  }

  std::string encodedText = context.context[encodedVar];
  std::map< char, std::string > huffmanCodes = codeContext.codeContext[codesVar];
  std::string decodedText;

  if (decompressText(encodedText, huffmanCodes, decodedText))
  {
    context.context[decodedVar] = decodedText;
    out << "Text decompressed into " << decodedVar << "\n";
  }
  else
  {
    out << "<INVALID DECOMPRESSION>\n";
  }
}

void skuratov::eff(std::istream& in, std::ostream& out, const Context& context, const CodeContext& codeContext)
{
  std::string textVar, codesVar;
  in >> textVar >> codesVar;

  if (context.context.find(textVar) == context.context.end() || codeContext.codeContext.find(codesVar) == codeContext.codeContext.end())
  {
    out << "<INVALID EFF>" << '\n';
    return;
  }

  std::string text = context.context.at(textVar);
  std::map< char, std::string > huffmanCodes = codeContext.codeContext.at(codesVar);

  double efficiency = calculateEfficiency(text, huffmanCodes);

  out << "Original size: " << text.size() * 8 << " bits\n";
  out << "Compressed size: " << efficiency << " bits\n";
  out << "Compression efficiency: " << efficiency << "%\n";
}

void skuratov::sortData(std::istream& in, std::ostream& out, Context& context)
{
  std::string textVar;
  in >> textVar;

  if (context.context.find(textVar) == context.context.end())
  {
    out << "<INVALID SORT DATA>" << '\n';
    return;
  }

  std::string text = context.context[textVar];
  std::istringstream iss(text);
  std::vector< std::string > words((std::istream_iterator< std::string > (iss)), std::istream_iterator< std::string >());
  std::sort(words.begin(), words.end());

  std::ostringstream oss;
  std::copy(words.begin(), words.end(), std::ostream_iterator< std::string >(oss, " "));
  context.context[textVar] = oss.str();

  out << "Data sorted in " << textVar << "\n";
}

void skuratov::removeDuplicates(std::istream& in, std::ostream& out, Context& context)
{
  std::string textVar;
  in >> textVar;

  if (context.context.find(textVar) == context.context.end()) {
    out << "<INVALID DUPLICATES REMOVAL>" << '\n';
    return;
  }
  std::string text = context.context[textVar];
  std::istringstream iss(text);
  std::set< std::string > uniqueWords((std::istream_iterator< std::string >(iss)), std::istream_iterator< std::string >());

  std::ostringstream oss;
  std::copy(uniqueWords.begin(), uniqueWords.end(), std::ostream_iterator< std::string >(oss, " "));
  context.context[textVar] = oss.str();

  out << "Duplicates removed in " << textVar << "\n";
}

void skuratov::countWords(std::istream& in, std::ostream& out, const Context& context)
{
  std::string textVar;
  in >> textVar;

  if (context.context.find(textVar) == context.context.end())
  {
    out << "<INVALID WORD COUNT>" << '\n';
    return;
  }

  std::string text = context.context.at(textVar);
  std::istringstream iss(text);
  size_t wordCount = std::distance(std::istream_iterator< std::string >(iss), std::istream_iterator< std::string >());

  out << "Word count in " << textVar << ": " << wordCount << "\n";
}
