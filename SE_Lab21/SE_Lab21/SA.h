#pragma once
#include "stdafx.h"
#include "LT.h"
#include "Error.h"
#include "IT.h"
#include "Error.h"
#include <iostream>
#include <stack>
#include <list>
#include <vector>

namespace SA
{
	void performSemanticAnalysis(LT::LexTable, IT::IdTable);
}