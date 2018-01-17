(use-modules (opencog) (opencog query))

(load "reduct.scm")

;; Tests for negation involution rule.

(define X (Predicate "X"))

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

;; Tests for minus involution rule.

(define three (Number "3"))

;; -(-3) = 3
(define test_1_num (Minus (Minus three)))

;; -(-(-3)) = -3
(define test_2_num (Minus (Minus (Minus three))))

;; -(-(-(-3))) = 3
(define test_3_num (Minus (Minus (Minus (Minus three)))))

(reduce test_3)

;(reduce test_3_num)
