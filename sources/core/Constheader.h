#pragma once

#include <map>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <qglobal.h>
#include <QString>
#include <QDebug>

#include "FastSerializer.h"

const int SIZE_H_SQ = 12; // visible size const
const int SIZE_W_SQ = 12;

extern bool NODRAW; // probably nodraw mode

enum class Dir : int
{
    ALL = -1,
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
    ZUP = 4,
    ZDOWN = 5,

    SOUTHEAST = 6,
    SOUTHWEST = 7,
    NORTHEAST = 8,
    NORTHWEST = 9,
};

inline FastSerializer& operator<<(FastSerializer& file, const Dir& dir)
{
    file << static_cast<int>(dir);
    return file;
}

inline FastDeserializer& operator>>(FastDeserializer& file, Dir& dir)
{
    int temp;
    file >> temp;
    dir = static_cast<Dir>(temp);
    return file;
}

namespace kv
{

struct Vector
{
    Vector() : Vector(0, 0, 0) { }
    Vector(int new_x, int new_y, int new_z)
        : x(new_x), y(new_y), z(new_z) { }
    int x;
    int y;
    int z;
};

struct Position
{
    Position() : Position(0, 0, 0) { }
    Position(int new_x, int new_y, int new_z)
        : x(new_x), y(new_y), z(new_z) { }
    bool operator==(const Position& other) const
    {
        return (x == other.x) && (y == other.y) && (z == other.z);
    }
    bool operator!=(const Position& other) const
    {
        return !operator==(other);
    }

    int x;
    int y;
    int z;
};

inline uint qHash(const kv::Position& point, uint seed = 0)
{
    uint retval = 59;
    retval = retval * 13 + ::qHash(point.z, seed);
    retval = retval * 13 + ::qHash(point.x, seed);
    retval = retval * 13 + ::qHash(point.y, seed);
    return retval;
}

}

inline FastDeserializer& operator>>(FastDeserializer& file, kv::Vector& vdir)
{
    file >> vdir.x;
    file >> vdir.y;
    file >> vdir.z;
    return file;
}

inline FastSerializer& operator<<(FastSerializer& file, const kv::Vector& vdir)
{
    file << vdir.x;
    file << vdir.y;
    file << vdir.z;
    return file;
}

inline unsigned int hash(const kv::Vector& vdir)
{
    return    (vdir.x + 1)
           + ((vdir.y + 1) << 8)
           + ((vdir.z + 1) << 16);
}

inline FastDeserializer& operator>>(FastDeserializer& file, kv::Position& position)
{
    file >> position.x;
    file >> position.y;
    file >> position.z;
    return file;
}

inline FastSerializer& operator<<(FastSerializer& file, const kv::Position& position)
{
    file << position.x;
    file << position.y;
    file << position.z;
    return file;
}

inline unsigned int hash(const kv::Position& position)
{
    return    (position.x + 1)
           + ((position.y + 1) << 8)
           + ((position.z + 1) << 16);
}

inline bool IsNonZero(const kv::Vector& vdir)
{
    return    vdir.x
           || vdir.y
           || vdir.z;
}

const kv::Vector VD_LEFT(-1, 0, 0); // west
const kv::Vector VD_RIGHT(1, 0, 0); // east
const kv::Vector VD_UP(0, -1, 0); // north
const kv::Vector VD_DOWN(0, 1, 0); // south
const kv::Vector VD_ZUP(0, 0, 1);
const kv::Vector VD_ZDOWN(0, 0, -1);

namespace helpers
{
    const kv::Vector DirToVDir[6] = {VD_LEFT, VD_RIGHT, VD_UP, VD_DOWN, VD_ZUP, VD_ZDOWN};
}
inline kv::Vector DirToVDir(Dir dir)
{
    // TODO: switch
    int index = static_cast<int>(dir);
    return helpers::DirToVDir[index];
}

inline Dir VDirToDir(const kv::Vector& vdir)
{
    int abs_x = std::abs(vdir.x);
    int abs_y = std::abs(vdir.y);
    int abs_z = std::abs(vdir.z);
    if ((abs_x > abs_y) && (abs_x > abs_z))
    {
        if (vdir.x > 0)
        {
            return Dir::RIGHT;
        }
        return Dir::LEFT;
    }
    if (abs_y >= abs_z)
    {
        if (vdir.y >= 0)
        {
            return Dir::DOWN;
        }
        return Dir::UP;
    }

    if (vdir.z > 0)
    {
        return Dir::ZUP;
    }
    return Dir::ZDOWN;
}

inline Dir RevertDir(Dir dir)
{
    switch (dir)
    {
    case Dir::UP:
        return Dir::DOWN;
    case Dir::DOWN:
        return Dir::UP;
    case Dir::LEFT:
        return Dir::RIGHT;
    case Dir::RIGHT:
        return Dir::LEFT;
    case Dir::ZUP:
        return Dir::ZDOWN;
    case Dir::ZDOWN:
        return Dir::ZUP;
    case Dir::NORTHEAST:
        return Dir::SOUTHWEST;
    case Dir::SOUTHWEST:
        return Dir::NORTHEAST;
    case Dir::SOUTHEAST:
        return Dir::NORTHWEST;
    case Dir::NORTHWEST:
        return Dir::SOUTHEAST;
    }
}

const int MAX_LEVEL = 20;
