;; =============================================================================
;; Involution.
;;
;; An involution is a function that, when applied twice, brings one back to the
;; starting point.
;;              f(f(x)) = x for all x in the domain of f.
;; See https://en.wikipedia.org/wiki/Involution_(mathematics)) for more details.
;; -----------------------------------------------------------------------------

;; list of involuntary functions.
(define involuntary_functions (Concept "involuntary functions"))

(Member (Predicate "Not") involuntary_functions)

(define involution-rule
    (BindLink

        ;; list of variables.
        (VariableList
            (TypedVariable (Variable "$f") (Type "PredicateNode"))
            (Variable "$x")
        )

        ;; If function f is one of the involuntary functions, then f(f(x)) = x.
        (AndLink
            (Evaluation
                (Variable "$f")
                (Evaluation
                    (Variable "$f")
                    (Variable "$x")))
            (Member
                (Variable "$f")
                involuntary_functions))

        (Variable "$f")
))

(define involution-rule-name (DefinedSchema "involution-rule"))

(Define involution-rule-name involution-rule)

(define get-involuntaries
    (GetLink
        (AndLink
            (Evaluation
                (Variable "$f")
                (Evaluation
                    (Variable "$f")
                    (Variable "$x")))
            (Member
                (Variable "$f")
                involuntary_functions))
))