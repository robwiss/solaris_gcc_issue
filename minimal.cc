#include <stdio.h>

#include "Impl.h"

int main()
{
    const char *data_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
" BadTag>\n"
"  <Description>\n"
"    Some data\n"
"  </Description>\n"
"</BadTag>\n";

    Impl i;
    try
    {
        i.func(data_xml);
    }
    catch (MyException &e)
    {
        printf("MyException: %s\n", e.msg.c_str());
    }

    return 0;
}
