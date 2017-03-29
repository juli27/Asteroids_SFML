//#include "FileParser.hpp"
//
//FileParser::FileParser(std::string Filename) :
//	m_File(Filename)
//{
//	parseFile();
//}
//
//void FileParser::parseFile()
//{
//	while (!m_File.eof())
//	{
//		std::pair<std::string, std::string> Entry;
//		std::string Key, Data;
//		char *Buffer;
//
//		m_File.get(Buffer, sizeof(char) * 1024, ' ');
//		Key = Buffer;
//
//		m_File.get(Buffer, sizeof(char) * 1024, '\n');
//		Data = Buffer;
//
//		Entry = std::make_pair(Key, Data);
//		m_Entrys.insert(Entry);
//	}
//}
//
//std::string FileParser::getDataFromKey(std::string Key) const
//{
//	std::map<std::string, std::string>::const_iterator It;
//	It = m_Entrys.find(Key);
//
//	return It->second;
//}