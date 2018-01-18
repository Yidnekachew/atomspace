(define (return-value x) x)

;(define evaluate-constant-pattern-with-not
; (Bind
;;  (Quote
;   (Not (Not
;;         (Unquote
;          (Predicate "X")
;;         )
;   ))
;;  )
;
;  (Predicate "Y")))

;(Not (Not (Predicate "Y")))

;(cog-execute! evaluate-constant-pattern-with-not)

(define test
 (BindLink
  (LocalQuoteLink (NotLink (NotLink (PredicateNode "X"))))

  (ExecutionOutputLink
   (GroundedSchemaNode "scm: return-value")
   (PredicateNode "X")))
)

(cog-execute! test)