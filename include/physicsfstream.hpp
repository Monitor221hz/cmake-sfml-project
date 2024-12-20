//https://github.com/SFML/SFML/wiki/Source%3A-PhysicsFS-Input-Stream
#pragma once
#include <SFML/System/InputStream.hpp>
#include <SFML/System/NonCopyable.hpp>

struct PHYSFS_File;

class PhysFsStream : public sf::InputStream, sf::NonCopyable
{
public:
    PhysFsStream(const char * filename = 0x0);
    virtual ~PhysFsStream();
    bool isOpen() const;
    bool open(const char * filename);
    void close();
    virtual sf::Int64 read(void * data, sf::Int64 size);
    virtual sf::Int64 seek(sf::Int64 position);
    virtual sf::Int64 tell();
    virtual sf::Int64 getSize();

private:
    PHYSFS_File * m_File;

};