(use-modules (opencog) (opencog query))

(load "reduct.scm")

;; Tests for addition commutativity rule.

(define four (Number "4"))

(define five (Number "3"))

;; 4 + 5 = 5 + 4
(define test_1 (Plus four five))

(reduce test_1)

