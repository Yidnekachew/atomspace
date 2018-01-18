;; =============================================================================
;; Commutativity.
;;
;; A binary operation is commutative if changing the order of the operands
;; does not change the result.
;;              f(a,b) = f(b,a)
;;
;; Operations which have commutative property include:
;;           - Addition of real numbers
;;           - Multiplication of real numbers
;;           - Boolean And, Or, Nand, Iff, Nor
;;
;; See https://en.wikipedia.org/wiki/Commutative_property for more details.
;; -----------------------------------------------------------------------------

;; The rule should say f(x,y) = f(y,x).

(define (return-value x) x)

;; Generate commutativity rule for different link types.
(define (gen-commutativity-rule link-type var-type)
 (let* ((X (Variable "$X"))
        (Y (Variable "$Y"))
        (FXY (link-type X Y))
        (FYX (link-type Y X)))
  (Bind
   ;; Variables list
   (VariableList
    (TypedVariable X var-type)
    (TypedVariable Y var-type))

   ;; f(x,y)
   (And FXY)

   ;; return f(y,x)
   (ExecutionOutput
    (GroundedSchemaNode "scm: return-value")
    (List FYX))
  )))

;; Generate commutativity rule for addition.
(define addition-commutativity-rule
 (let ((var-type (TypeNode "NumberNode")))
  (gen-commutativity-rule PlusLink var-type)))

(define addition-commutativity-rule-name
 (DefinedSchema "addition-commutativity-rule"))

(Define addition-commutativity-rule-name addition-commutativity-rule)