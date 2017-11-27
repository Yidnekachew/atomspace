(define parent-as (cog-atomspace))

(define derived-as (cog-new-atomspace parent-as))

(cog-set-atomspace! derived-as)

(Inheritance (Concept "x") (Concept "b"))

(define rule
	(Bind
	 (VariableList
		(TypedVariable (Variable "$x") (Type "ConceptNode"))
	 )

		(Inheritance (Variable "$x") (Concept "b"))

		(Concept "b")))

(cog-set-atomspace! parent-as)

(cog-execute! rule)

; =========
; Constant clauses created in the child atomspace shouldn't belong to the parent atomspace. 

; But, in this scenario, a rule created in the child atomspace when queried against the parent atomspace considers constant clauses found only in the derived atomspace.

; ```
; (define parent-as (cog-atomspace))

; (define derived-as (cog-new-atomspace parent-as))

; (cog-set-atomspace! derived-as)

; (define rule
; 	(Bind
; 		(Inheritance (Concept "a") (Concept "b"))
; 
; 		(Concept "b")))

; (cog-set-atomspace! parent-as)

; (cog-bind rule)
; ```
; evaluates to: 
; ```
; $1 = (SetLink
;    (ConceptNode "b")
; )
; ```
; when the expected result is an empty  `(SetLink )`
