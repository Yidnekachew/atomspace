#include <opencog/atomspace/AtomSpace.h>
#include <opencog/rule-engine/forwardchainer/ForwardChainer.h>
#include <opencog/guile/SchemeEval.h>
#include <opencog/query/BindLinkAPI.h>

using namespace opencog;

int main(int argc, char** args)
{
	AtomSpace as;

	std::cout << "Reduct using Forward chaining:\n";

	SchemeEval *eval = SchemeEval::get_evaluator(&as);

	eval->eval("(load \"involution/involution_rule.scm\")");
	eval->eval("(load \"involution/reduct.scm\")");
	std::string result = eval->eval("(load \"involution/test.scm\")");
	std::cout << "Reduction result: \n" << result << std::endl;
	return 0;
}
