(use-modules (opencog query))
(use-modules (opencog exec))

(load "reduct.scm")

(define x (Concept "X"))

(define not (Predicate "Not"))

;; ~X = ~X
(define test_1 (Evaluation not x))

;; ~(~X) = X
(define test_2 (Evaluation not test_1))

;; ~(~(~X)) = ~X
(define test_3 (Evaluation not test_2))

;; ~(~(~(~X))) = X
(define test_4 (Evaluation not test_3))

;; ~(~(~(~(~X)))) = ~X
(define test_5 (Evaluation not test_4))

;; ~(~X) && ~(~X) = X && X
(define test_6 (And test_2 test_2))

;; ~(~X) || ~(~X) = X || X
(define test_7 (Or test_2 test_2))

;; `Up` isn't a member of involutary functions. So, the ff shouldn't be reduced by involution.
(define test_8
    (Evaluation
        (Predicate "Up")
        (Evaluation
            (Predicate "Up")
            (Concept "X"))))

;(cog-execute! involution-rule)

;(reduce test_8)
