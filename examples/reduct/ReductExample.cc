#include <opencog/atomspace/AtomSpace.h>
#include <opencog/rule-engine/forwardchainer/ForwardChainer.h>
#include <opencog/guile/SchemeEval.h>
#include <opencog/query/BindLinkAPI.h>

using namespace opencog;

int main(int argc, char** args)
{
    AtomSpace as;

    std::cout << "\n Reduct using Forward chaining:\n";

    SchemeEval *eval = SchemeEval::get_evaluator(&as);

    eval->eval("(use-modules (opencog))");
    eval->eval("(use-modules (opencog rule-engine))");
    eval->eval("(use-modules (opencog query))");
    eval->eval("(use-modules (opencog exec))");

//    eval->eval("(load \"involution/involution_rule.scm\")");
//    eval->eval("(load \"involution/reduct.scm\")");
//    std::string result = eval->eval("(load \"involution/test.scm\")");

    std::string result = eval->eval("(load \"test/test4.scm\")");
	std::cout << "Reduction result:" << std::endl;
	std::cout << result << std::endl;

//	AtomSpace derived_as(&as);
//
//	Handle A = derived_as.add_node(CONCEPT_NODE, "A"),
//			B = derived_as.add_node(CONCEPT_NODE, "B");
//
//	Handle bl = derived_as.add_link(
//			BIND_LINK, derived_as.add_link(INHERITANCE_LINK, A, B), B),
//			result = bindlink(&derived_as, bl),
//			expected = as.add_link(SET_LINK);
//
//	std::cout << "Expected Result:" << std::endl;
//	std::cout << expected->to_string() << std::endl;
//
//    std::cout << "Reduction result:" << std::endl;
//    std::cout << result->to_string() << std::endl;

    return 0;
}
