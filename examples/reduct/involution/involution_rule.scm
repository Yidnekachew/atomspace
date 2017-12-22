;; =============================================================================
;; Involution.
;;
;; An involution is a function that, when applied twice, brings one back to the
;; starting point.
;;              f(f(x)) = x for all x in the domain of f.
;; See https://en.wikipedia.org/wiki/Involution_(mathematics) for more details.
;; -----------------------------------------------------------------------------

(define (return-value x) x)

;; Generate involution rule for different link types.
(define (gen-involution-rule link-type var-type)
 (let* ((X (Variable "$X"))
        (FFX (link-type (link-type X))))
  (Bind
   ;; Variables list
   (VariableList
    (TypedVariable X var-type))

   ;; f(f(x))
   (And FFX)

   ;; return X
   (ExecutionOutput
    (GroundedSchemaNode "scm: return-value")
    (List X))
  )))

;; Generate involution rule for boolean negation.
(define negation-involution-rule
 (let ((var-type (TypeChoice
                  (TypeNode "ConceptNode")
                  (TypeNode "AndLink")
                  (TypeNode "OrLink")
                  (TypeNode "NotLink"))))
  (gen-involution-rule NotLink var-type)))

(define negation-involution-rule-name
 (DefinedSchema "negation-involution-rule"))

(Define negation-involution-rule-name negation-involution-rule)

;; Generate involution rule for numeric negation.
(define minus-involution-rule
 (gen-involution-rule MinusLink (TypeNode "NumberNode")))

(define minus-involution-rule-name
 (DefinedSchema "minus-involution-rule"))

(Define minus-involution-rule-name minus-involution-rule)
