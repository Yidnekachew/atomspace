(use-modules (opencog rule-engine))
(use-modules (opencog query))
(use-modules (opencog exec))

(define (return-value x) x)

(define rule
    (BindLink

        (AndLink
            (Evaluation
                (Variable "$f")
                (Evaluation
                    (Variable "$f")
                    (Variable "$x")))
            (Member
                (Variable "$y")
                (Variable "$z")))

        (ExecutionOutputLink
            (GroundedSchemaNode "scm: return-value")
            (Set (Variable "$x") (Variable "$f") (Variable "$y")))))

(define rule-name (DefinedSchema "rule"))

(Define rule-name rule)

(define rule-base (Concept "rule-base"))

(Inheritance
    rule-base
    (Concept "URE"))

(define rules
    (list
        rule-name
    ))

(ure-add-rules rule-base rules)

(ure-set-num-parameter rule-base "URE:maximum-iterations" 2)

(cog-fc rule-base
    (Evaluation
            (Predicate "func")
            (Evaluation
                (Predicate "func")
                (Concept "X"))))

;; Stops with (?????????????????)
; ERROR: In procedure opencog-extension:
; ERROR: Stack overflow