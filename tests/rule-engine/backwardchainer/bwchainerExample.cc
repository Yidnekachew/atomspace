#include <opencog/atomspace/AtomSpace.h>
#include <opencog/rule-engine/backwardchainer/BackwardChainer.h>
#include <opencog/rule-engine/forwardchainer/ForwardChainer.h>
#include <opencog/guile/SchemeEval.h>
#include <opencog/rule-engine/URELogger.h>

void test_conditional_instantiation_1(AtomSpace &_as);

void test_constant_pattern_2(AtomSpace& _as);

void test_unsatisfied_premise(AtomSpace& _as);

string load_from_path(const string& filename, AtomSpace& _as);

#define an _as.add_node
#define al _as.add_link

int main(int argc, char** args)
{
    AtomSpace as;
//	SchemeEval *_eval = SchemeEval::get_evaluator(&as);
//
//    logger().set_level(Logger::DEBUG);
//    logger().set_timestamp_flag(false);
//    // logger().set_sync_flag(true);
//    logger().set_print_to_stdout_flag(true);
//    ure_logger().set_level(Logger::INFO);
//    // ure_logger().set_timestamp_flag(false);
//    // ure_logger().set_sync_flag(true);
//    // ure_logger().set_print_to_stdout_flag(true);
//    randGen().seed(0);
//
//    string cur_ppp_dir = string(PROJECT_SOURCE_DIR),
//        cur_pp_dir = cur_ppp_dir + "/tests",
//        cur_p_dir = cur_pp_dir + "/rule-engine",
//        cur_dir = cur_p_dir + "/backwardchainer";
//    vector<string> load_paths = {cur_ppp_dir, cur_pp_dir, cur_p_dir, cur_dir};
//    for (string& p : load_paths)
//    {
//        string eval_str = string("(add-to-load-path \"") + p + string("\")");
//        _eval->eval(eval_str);
//    }
//    _eval->eval("(use-modules (opencog))");
//    _eval->eval("(use-modules (opencog rule-engine))");
//    _eval->eval("(use-modules (opencog logger))");
//
//    std::cout << "\n Backward Chaining \n";
//    test_conditional_instantiation_1(as);

//    test_constant_pattern_2(as);

	test_unsatisfied_premise(as);

    return 0;
}

string load_from_path(const string& filename, AtomSpace& _as)
{
    SchemeEval *_eval = SchemeEval::get_evaluator(&_as);
    return _eval->eval(string("(load-from-path \"") + filename + "\")");
}

void test_conditional_instantiation_1(AtomSpace &_as)
{
    logger().debug("BEGIN TEST: %s", __FUNCTION__);

    string result = load_from_path("conditional-instantiation-config.scm", _as);

    logger().debug() << "result = " << result;

    result = load_from_path("friends.scm", _as);
    randGen().seed(0);

    Handle top_rbs = _as.get_node(CONCEPT_NODE, UREConfig::top_rbs_name);

    Handle are_friends = an(PREDICATE_NODE, "are-friends"),
        john = an(CONCEPT_NODE, "John"),
        mary = an(CONCEPT_NODE, "Mary"),
        edward = an(CONCEPT_NODE, "Edward"),
        cyril = an(CONCEPT_NODE, "Cyril");
    auto friend_with_john = [&](const Handle& h) {
        return al(EVALUATION_LINK, are_friends, al(LIST_LINK, h, john));
    };
    Handle target_var = an(VARIABLE_NODE, "$who"),
        target = friend_with_john(target_var),
        vardecl = al(VARIABLE_LIST,
                     al(TYPED_VARIABLE_LINK,
                        target_var, an(TYPE_NODE, "ConceptNode")));

    BackwardChainer bc(_as, top_rbs, target, vardecl);
    bc.get_config().set_maximum_iterations(40);
    bc.do_chain();

    Handle results = bc.get_results(),
        expected = al(SET_LINK,
                      friend_with_john(mary),
                      friend_with_john(edward),
                      friend_with_john(cyril));

    logger().debug() << "results = " << results->to_string();
    logger().debug() << "expected = " << expected->to_string();

    logger().debug("END TEST: %s", __FUNCTION__);
}

void test_constant_pattern_2(AtomSpace& _as)
{
    Handle mary = an(CONCEPT_NODE, "Mary"),
        edward = an(CONCEPT_NODE, "Edward");

    SchemeEval* eval = SchemeEval::get_evaluator(&_as);

    string dir = string(PROJECT_SOURCE_DIR) + "/tests/query";

    eval->eval(string("(add-to-load-path \"") + dir + string("\")"));

    eval->eval("(use-modules (opencog))");
    eval->eval("(use-modules (opencog exec))");
    eval->eval("(use-modules (opencog query))");
    eval->eval("(use-modules (opencog logger))");

	logger().set_level(Logger::FINE);
	logger().set_timestamp_flag(false);
	logger().set_sync_flag(true);
	ure_logger().set_level(Logger::INFO);
	randGen().seed(0);

    eval->eval("(load-from-path \"friends.scm\")");

    Handle result = eval->eval_h("(cog-execute! constant-clause-with-variable)"),
        expected = al(SET_LINK, edward, mary);

    std::cout << "result " << result->to_short_string();

    std::cout << "expected " << expected->to_short_string();

//    TS_ASSERT_EQUALS(result, expected);
}

void test_unsatisfied_premise(AtomSpace& _as)
{
	SchemeEval* _eval = SchemeEval::get_evaluator(&_as);

	string dir = string(PROJECT_SOURCE_DIR) + "/tests/rule-engine/backwardchainer";
	_eval->eval(string("(add-to-load-path \"") + dir + string("\")"));
	_eval->eval("(load-from-path \"fc-unsatisfied-premise.scm\")");

	Handle expected = al(SET_LINK ),
		table = an(CONCEPT_NODE, "table"),
		furniture = an(CONCEPT_NODE, "furniture"),
		source = al(INHERITANCE_LINK, table, furniture),
		vardecl = Handle::UNDEFINED,
		top_rbs = _as.get_node(CONCEPT_NODE, "rule-base");

    ForwardChainer fc(_as, top_rbs, table, vardecl);
    fc.get_config().set_maximum_iterations(20);
    fc.do_chain();

    UnorderedHandleSet results = fc.get_chaining_result();

	results.find(expected);

	std::cout << "results " << oc_to_string(results);
}