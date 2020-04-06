#pragma once

#define ASSERT(condition) do{if(!(condition)){return 0;}}while(false)
#define WHITESPACE() do{std::cout<<std::endl;}while(false)