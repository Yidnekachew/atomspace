(use-modules (opencog) (opencog query) (opencog exec))

(load "reduct.scm")

(define X (Concept "X"))

(define three (Number "3"))

;; ~X = ~X
(define test_1 (Not X))

;; ~(~X) = X
(define test_2 (Not (Not X)))

;; ~(~(~X)) = ~X
(define test_3 (Not (Not (Not X))))

;; ~(~(~(~X))) = X
(define test_4 (Not (Not (Not (Not X)))))

;; ~(~(~(~(~X)))) = ~X
(define test_5 (Not (Not (Not (Not (Not X))))))

;; ~(~X) && ~(~X) = X && X
(define test_6 (And (Not (Not X)) (Not (Not X))))

;; ~(~X) || ~(~X) = X || X
(define test_7 (Or (Not (Not X)) (Not (Not X))))

;; -(-3) = 3
(define test_1_num (Minus (Minus three)))

;(cog-execute! involution-rule)

(reduce test_2)

;(reduce test_1_num)
