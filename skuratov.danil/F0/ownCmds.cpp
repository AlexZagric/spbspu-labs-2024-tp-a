#include "ownCmds.hpp"

void skuratov::help(std::ostream& out)
{
  setlocale(LC_ALL, "Russian");
  out << "load <text1> <text1.txt> - �������� ���������������� ������ �� �����\n";
  out << "huff <codes1> <text1> - �������� ��������� ��� �� �������������� ������\n";
  out << "compress <encoded1> <text1> <codes1> - ������ ������\n";
  out << "save <encoded1> <output1.bin> - ���������� ������\n";
  out << "load_encoded <text3> <codes1> <output1.bin> - �������� �������������� ������ �� �����\n";
  out << "decompress <decoded1> <text3> <codes1> -  �������������� ������� �����\n";
  out << "eff text1 codes1 - ����� ������������� ������ ������\n";
  out << "sort_data <encoded1> - ���������� ������\n";
  out << "remove_duplicates <text1> - �������� ������������� ���� �� ������\n";
  out << "count_words <text1> - ������� ���������� ���� � ������\n";
}

void skuratov::load()
{}

void skuratov::huff()
{}

void skuratov::compress()
{}

void skuratov::save()
{}

void skuratov::loadEncoded()
{}

void skuratov::decompress()
{}

void skuratov::eff()
{}

void skuratov::sortData()
{}

void skuratov::removeDuplicates()
{}

void skuratov::countWords()
{}
