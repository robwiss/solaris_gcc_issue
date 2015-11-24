#include "Impl.h"
#include "MyData.h"
#include "Util.h"

#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>

MyData Impl::func(const std::string &xml) const
{
    // Load xml document
    auto doc = scoped_cptr(
        xmlReadMemory(xml.c_str(), xml.size() + 1, "noname.xml", nullptr, 0),
        xmlFreeDoc
    );
    if (nullptr == doc)
    {
        throw MyException("ohno");
    }
}
