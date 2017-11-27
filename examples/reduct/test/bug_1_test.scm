;; The problem lies in Rule.cc:383
;; I think, when doing unification, it doesn't go
;; for unifying anything other than variables.

(use-modules (opencog rule-engine))
(use-modules (opencog query))
(use-modules (opencog exec))

(define (return-value x) x)

(define rule
    (BindLink

        (VariableList
            (TypedVariable (Variable "$a") (Type "ConceptNode")))

        (Inheritance
            (Variable "$a")
            (Concept "furniture"))

        (ExecutionOutput
        	(GroundedSchemaNode "scm: return-value")
        	(Inheritance (Variable "$a") (Concept "animal")))))

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
;   (InheritanceLink
;      (ConceptNode "furniture")
;      (ConceptNode "animal")
;   )
;   (InheritanceLink
;      (ConceptNode "animal")
;      (ConceptNode "animal")
;   )
;)

(And
    (Inheritance
        (Variable "table")
        (Variable "furniture"))

    (Member
        (Variable "$c")
        (Variable "$d")))