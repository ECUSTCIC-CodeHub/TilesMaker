#include <iostream>
#include "TestLink.h"
#include "ToolsTestLink.h"

TestLink::TestLink()
{
}

TestLink::~TestLink()
{
}

void TestLink::Test()
{
    std::cout << "Link successful\n";
    ToolsTestLink tools;
    tools.Test();
}