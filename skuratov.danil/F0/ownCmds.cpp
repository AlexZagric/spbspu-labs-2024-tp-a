#include "ownCmds.hpp"

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

void skuratov::load(std::istream& in, std::ostream& out)
{}

void skuratov::huff(std::istream& in, std::ostream& out)
{}

void skuratov::compress(std::istream& in, std::ostream& out)
{}

void skuratov::save(std::istream& in, std::ostream& out)
{}

void skuratov::loadEncoded(std::istream& in, std::ostream& out)
{}

void skuratov::decompress(std::istream& in, std::ostream& out)
{}

void skuratov::eff(std::istream& in, std::ostream& out)
{}

void skuratov::sortData(std::istream& in, std::ostream& out)
{}

void skuratov::removeDuplicates(std::istream& in, std::ostream& out)
{}

void skuratov::countWords(std::istream& in, std::ostream& out)
{}
