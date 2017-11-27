;(define rule
; (Bind
;	(Concept "a")
;	(Concept "b")
; )
;)

(define rule
 (Bind
  (And
   (Inheritance (Concept "a") (Concept "b"))
   (Concept "a")
  )

  (Concept "c")
 )
)

(cog-execute! rule)
