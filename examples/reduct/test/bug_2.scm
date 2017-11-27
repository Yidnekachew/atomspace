;; The problem lies in Rule.cc:381
;; I think the for loop makes it to return a unified source
;; even if only one of the premises is satisfied.

(use-modules (opencog rule-engine))
(use-modules (opencog query))
(use-modules (opencog exec))

(define (return-value x) x)

(define rule
    (BindLink
        (VariableList
            (TypedVariable (Variable "$a") (Type "ConceptNode"))
            (TypedVariable (Variable "$b") (Type "ConceptNode"))
            (TypedVariable (Variable "$c") (Type "ConceptNode"))
            (TypedVariable (Variable "$d") (Type "ConceptNode"))
        )

        (And
            (Inheritance
                (Variable "$a")
        		(Variable "$b"))
        	(Member
        		(Variable "$c")
        		(Variable "$d")))

        (ExecutionOutput
        	(GroundedSchemaNode "scm: return-value")
        	(Inheritance (Variable "$a") (Variable "$b")))))

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

(cog-fc rule-base (Inheritance (Concept "table") (Concept "furniture")))

;; Evaluates to
; $1 = (SetLink
;     (InheritanceLink
;        (ConceptNode "table")
;        (ConceptNode "furniture")
;     )
;  )

;(cog-fc rule-base
;    (Set
;        (Inheritance (Concept "table") (Concept "furniture"))
;        (Member (Concept "a") (Concept "b"))))

;; Evaluates to
;$1 = (SetLink
;    (InheritanceLink
;       (VariableNode "$a-648d8b51")
;       (VariableNode "$b-122f6b4d")
;    )
;    (InheritanceLink
;       (ConceptNode "table")
;       (ConceptNode "furniture")
;    )
;)