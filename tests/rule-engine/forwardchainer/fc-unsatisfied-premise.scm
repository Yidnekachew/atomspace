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
         (TypedVariable (Variable "$d") (Type "ConceptNode")))

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
