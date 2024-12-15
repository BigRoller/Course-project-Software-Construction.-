#pragma once
#include "LT.h"
#include "IT.h"
#include <stack>
#include <vector>

#define MAX_TOKEN_COUNT 30

namespace PN
{
	void PolishNotation(LT::LexTable&, IT::IdTable&);
}
