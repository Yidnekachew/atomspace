;; for all f, x where f is an involutary function, f(f(x)) = x.
(define involution-rule
 (BindLink
  ;; vars : f, x
  (VariableList
;   (Variable "$x")
   (TypedVariable
    (Variable "$f") (TypeChoice
                        (Type "NotLink")
                        (Type "OrLink"))))

;  f(f(x))
;  (Variable "$f" (Variable "$x"))
  (Inheritance
   (Variable "$f")
   (Variable "$f")
  )

  ;; = x.
  (Variable "$f")))

(Inheritance (Not (Concept "Some")) (Not (Concept "Some")))
(Inheritance (Not (Concept "Some")) (Not (Concept "Other")))
(Inheritance (Not (Concept "Some")) (Or (Concept "Other")))
(And (Concept "Another"))
(Or (Concept "Other"))

(cog-execute! involution-rule)