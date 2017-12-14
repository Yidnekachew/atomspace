(use-modules (opencog rule-engine))
(use-modules (opencog query))
(use-modules (opencog exec))

(define (return-value x) x)

(define rule
    (BindLink

        (And
            (Inheritance
                (Variable "$a")
        		(Variable "$b"))
        	(Member
        		(Variable "$c")
        		(Variable "$d")))

        (ExecutionOutput
        	(GroundedSchemaNode "scm: return-value")
        	(Set (Variable "$a") (Variable "$b")))))

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

(ure-set-num-parameter rule-base "URE:maximum-iterations" 20)

;(cog-fc rule-base (Inheritance (Concept "table") (Concept "furniture")))
;
;; Evaluates to
;$1 = (SetLink
;   (SetLink
;      (ConceptNode "table")
;      (ConceptNode "furniture")
;      (VariableNode "$c-4c2b3a57")
;   )
;)
