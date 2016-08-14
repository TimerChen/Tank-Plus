#ifndef TMAP_H
#define TMAP_H

#include <vector>
#include "Polygon.h"

namespace GAME
{
struct Tmap
{
	std::vector<Polygon> wall, badarea;
	std::vector<Point> birthplace;

	bool save(const char *filename);
	static void load(const char *filename, Tmap &tmap);
};
}

#endif // MAP_H
