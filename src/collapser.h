#pragma once

#include "datatypes.h"
#include "helpers.h"

coords find_lowest_entropy(matrix* cells, size_t num_tiles);

void update_neighbors(matrix* cells, coords loc);