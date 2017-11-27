(define parent-as (cog-atomspace))

(define derived-as (cog-new-atomspace parent-as))

(cog-set-atomspace! derived-as)

(Inheritance (Concept "a") (Concept "b"))

(define rule
 (Bind
  (VariableList
   (TypedVariable (Variable "$x") (Type "ConceptNode"))
   (TypedVariable (Variable "$y") (Type "ConceptNode")))

  (Inheritance (Variable "$x") (Variable "$y"))

  (Variable "$x")))

(cog-set-atomspace! parent-as)

(cog-execute! rule)