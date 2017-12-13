#include <opencog/atomspace/AtomSpace.h>
#include <opencog/rule-engine/backwardchainer/BackwardChainer.h>
#include <opencog/rule-engine/forwardchainer/ForwardChainer.h>
#include <opencog/guile/SchemeEval.h>
#include <opencog/rule-engine/URELogger.h>

void test_conditional_instantiation_1(AtomSpace &_as);

void test_constant_pattern_2(AtomSpace& _as);

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

    test_expand_1();

    return 0;
}

string load_from_path(const string& filename, AtomSpace& _as)
{
    SchemeEval *_eval = SchemeEval::get_evaluator(&_as);
    return _eval->eval((string("(load-from-path \"") + filename + "\")").c_str());
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

void test_expand_1()
{
    AndBIT andbit(_eval.eval_h("fcs-2"));
    Handle leaf = _eval.eval_h("(LambdaLink"
                                   "  (TypedVariableLink"
                                   "    (VariableNode \"$X\")"
                                   "    (TypeNode \"ConceptNode\"))"
                                   "  (EvaluationLink"
                                   "    (PredicateNode \"contain\")"
                                   "    (ListLink"
                                   "      (ConceptNode \"treatment-1\")"
                                   "      (ConceptNode \"compound-A\"))))");

    Rule closed_lambda_introduction_rule(closed_lambda_introduction_rule_h);
    RuleTypedSubstitutionMap rules =
        closed_lambda_introduction_rule.unify_target(leaf);
    RuleTypedSubstitutionPair rule = *rules.begin();

    AndBIT result = andbit.expand(leaf, rule, 1);
    AndBIT expected(
        _eval.eval_h("(BindLink"
                         "  (AndLink"
                         "    (EvaluationLink"
                         "      (GroundedPredicateNode \"scm: closed-lambda-introduction-precondition\")"
                         "      (EvaluationLink (stv 1.000000 1.000000)"
                         "        (PredicateNode \"contain\")"
                         "        (ListLink"
                         "          (ConceptNode \"treatment-1\")"
                         "          (ConceptNode \"compound-A\"))))"
                         "    (NotLink"
                         "      (IdenticalLink"
                         "        (LambdaLink"
                         "          (TypedVariableLink"
                         "            (VariableNode \"$X\")"
                         "            (TypeNode \"ConceptNode\"))"
                         "          (EvaluationLink"
                         "            (PredicateNode \"take\")"
                         "            (ListLink"
                         "              (VariableNode \"$X\")"
                         "              (ConceptNode \"treatment-1\"))))"
                         "        (LambdaLink"
                         "          (TypedVariableLink"
                         "            (VariableNode \"$X\")"
                         "            (TypeNode \"ConceptNode\"))"
                         "          (AndLink"
                         "            (EvaluationLink"
                         "              (PredicateNode \"contain\")"
                         "              (ListLink"
                         "                (ConceptNode \"treatment-1\")"
                         "                (ConceptNode \"compound-A\")))"
                         "            (EvaluationLink"
                         "              (PredicateNode \"take\")"
                         "              (ListLink"
                         "                (VariableNode \"$X\")"
                         "                (ConceptNode \"treatment-1\")))))))"
                         "    (NotLink"
                         "      (EqualLink"
                         "        (LambdaLink"
                         "          (TypedVariableLink"
                         "            (VariableNode \"$X\")"
                         "            (TypeNode \"ConceptNode\"))"
                         "          (EvaluationLink"
                         "            (PredicateNode \"contain\")"
                         "            (ListLink"
                         "              (ConceptNode \"treatment-1\")"
                         "              (ConceptNode \"compound-A\"))))"
                         "        (LambdaLink"
                         "          (TypedVariableLink"
                         "            (VariableNode \"$X\")"
                         "            (TypeNode \"ConceptNode\"))"
                         "          (EvaluationLink"
                         "            (PredicateNode \"take\")"
                         "            (ListLink"
                         "              (VariableNode \"$X\")"
                         "              (ConceptNode \"treatment-1\")))))))"
                         "  (ExecutionOutputLink"
                         "    (GroundedSchemaNode \"scm: deduction-formula\")"
                         "    (ListLink"
                         "      (ImplicationLink"
                         "        (LambdaLink"
                         "          (TypedVariableLink"
                         "            (VariableNode \"$X\")"
                         "            (TypeNode \"ConceptNode\"))"
                         "          (EvaluationLink"
                         "            (PredicateNode \"take\")"
                         "            (ListLink"
                         "              (VariableNode \"$X\")"
                         "              (ConceptNode \"treatment-1\"))))"
                         "        (LambdaLink"
                         "          (TypedVariableLink"
                         "            (VariableNode \"$X\")"
                         "            (TypeNode \"ConceptNode\"))"
                         "          (AndLink"
                         "            (EvaluationLink"
                         "              (PredicateNode \"contain\")"
                         "              (ListLink"
                         "                (ConceptNode \"treatment-1\")"
                         "                (ConceptNode \"compound-A\")))"
                         "            (EvaluationLink"
                         "              (PredicateNode \"take\")"
                         "              (ListLink"
                         "                (VariableNode \"$X\")"
                         "                (ConceptNode \"treatment-1\"))))))"
                         "      (ExecutionOutputLink"
                         "        (GroundedSchemaNode \"scm: implication-implicant-distribution-formula\")"
                         "        (ListLink"
                         "          (ImplicationLink"
                         "            (LambdaLink"
                         "              (TypedVariableLink"
                         "                (VariableNode \"$X\")"
                         "                (TypeNode \"ConceptNode\"))"
                         "              (EvaluationLink"
                         "                (PredicateNode \"take\")"
                         "                (ListLink"
                         "                  (VariableNode \"$X\")"
                         "                  (ConceptNode \"treatment-1\"))))"
                         "            (AndLink"
                         "              (LambdaLink"
                         "                (TypedVariableLink"
                         "                  (VariableNode \"$X\")"
                         "                  (TypeNode \"ConceptNode\"))"
                         "                (EvaluationLink"
                         "                  (PredicateNode \"take\")"
                         "                  (ListLink"
                         "                    (VariableNode \"$X\")"
                         "                    (ConceptNode \"treatment-1\"))))"
                         "              (LambdaLink"
                         "                (TypedVariableLink"
                         "                  (VariableNode \"$X\")"
                         "                  (TypeNode \"ConceptNode\"))"
                         "                (EvaluationLink"
                         "                  (PredicateNode \"contain\")"
                         "                  (ListLink"
                         "                    (ConceptNode \"treatment-1\")"
                         "                    (ConceptNode \"compound-A\"))))))"
                         "          (ExecutionOutputLink"
                         "            (GroundedSchemaNode \"scm: implication-introduction-formula\")"
                         "            (ListLink"
                         "              (ImplicationLink"
                         "                (LambdaLink"
                         "                  (TypedVariableLink"
                         "                    (VariableNode \"$X\")"
                         "                    (TypeNode \"ConceptNode\"))"
                         "                  (EvaluationLink"
                         "                    (PredicateNode \"take\")"
                         "                    (ListLink"
                         "                      (VariableNode \"$X\")"
                         "                      (ConceptNode \"treatment-1\"))))"
                         "                (LambdaLink"
                         "                  (TypedVariableLink"
                         "                    (VariableNode \"$X\")"
                         "                    (TypeNode \"ConceptNode\"))"
                         "                  (EvaluationLink"
                         "                    (PredicateNode \"contain\")"
                         "                    (ListLink"
                         "                      (ConceptNode \"treatment-1\")"
                         "                      (ConceptNode \"compound-A\")))))"
                         "              (LambdaLink"
                         "                (TypedVariableLink"
                         "                  (VariableNode \"$X\")"
                         "                  (TypeNode \"ConceptNode\"))"
                         "                (EvaluationLink"
                         "                  (PredicateNode \"take\")"
                         "                  (ListLink"
                         "                    (VariableNode \"$X\")"
                         "                    (ConceptNode \"treatment-1\"))))"
                         "              (ExecutionOutputLink"
                         "                (GroundedSchemaNode \"scm: closed-lambda-introduction-formula\")"
                         "                (ListLink"
                         "                  (LambdaLink"
                         "                    (TypedVariableLink"
                         "                      (VariableNode \"$X\")"
                         "                      (TypeNode \"ConceptNode\"))"
                         "                    (EvaluationLink"
                         "                      (PredicateNode \"contain\")"
                         "                      (ListLink"
                         "                        (ConceptNode \"treatment-1\")"
                         "                        (ConceptNode \"compound-A\"))))"
                         "                  (EvaluationLink"
                         "                    (PredicateNode \"contain\")"
                         "                    (ListLink"
                         "                      (ConceptNode \"treatment-1\")"
                         "                      (ConceptNode \"compound-A\")))))))))"
                         "      (ExecutionOutputLink"
                         "        (GroundedSchemaNode \"scm: implication-and-lambda-factorization-formula\")"
                         "        (ImplicationLink"
                         "          (AndLink"
                         "            (LambdaLink"
                         "              (TypedVariableLink"
                         "                (VariableNode \"$X\")"
                         "                (TypeNode \"ConceptNode\"))"
                         "              (EvaluationLink"
                         "                (PredicateNode \"take\")"
                         "                (ListLink"
                         "                  (VariableNode \"$X\")"
                         "                  (ConceptNode \"treatment-1\"))))"
                         "            (LambdaLink"
                         "              (TypedVariableLink"
                         "                (VariableNode \"$X\")"
                         "                (TypeNode \"ConceptNode\"))"
                         "              (EvaluationLink"
                         "                (PredicateNode \"contain\")"
                         "                (ListLink"
                         "                  (ConceptNode \"treatment-1\")"
                         "                  (ConceptNode \"compound-A\")))))"
                         "          (LambdaLink"
                         "            (TypedVariableLink"
                         "              (VariableNode \"$X\")"
                         "              (TypeNode \"ConceptNode\"))"
                         "            (AndLink"
                         "              (EvaluationLink"
                         "                (PredicateNode \"contain\")"
                         "                (ListLink"
                         "                  (ConceptNode \"treatment-1\")"
                         "                  (ConceptNode \"compound-A\")))"
                         "              (EvaluationLink"
                         "                (PredicateNode \"take\")"
                         "                (ListLink"
                         "                  (VariableNode \"$X\")"
                         "                  (ConceptNode \"treatment-1\"))))))))))"));

    logger().debug() << "result = " << oc_to_string(result);
    logger().debug() << "expected = " << oc_to_string(expected);

    TS_ASSERT_EQUALS(result, expected);
}