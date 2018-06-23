#include "../src/include/Template.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( template_test_0 )
{
 
    Template tmpl;
    

    BOOST_CHECK_EQUAL( tmpl.calculate_sqrt(4.0), 2.0 );
}
