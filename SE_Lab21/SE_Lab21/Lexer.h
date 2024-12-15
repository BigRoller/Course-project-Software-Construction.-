#pragma once
#include "LT.h"
#include "IT.h"
#include "FST.h"
#include "Error.h"
#include <vector>
#include <list>
#include <stack>

#define MAX_ID_LENGTH 15
#define MAX_LITERAL_LENGTH 100

std::string GetLexAndIdTable(LT::LexTable& lextable, IT::IdTable& idtable, char* str);