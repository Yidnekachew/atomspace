(use-modules (opencog rule-engine))

(load "involution_rule.scm")

(define reduct-rule-base (Concept "reduct-rule-base"))

(Inheritance
    reduct-rule-base
    (Concept "URE"))

(define reduct-rules
    (list
        involution-rule-name
    ))

(ure-add-rules reduct-rule-base reduct-rules)

(ure-set-num-parameter reduct-rule-base "URE:maximum-iterations" 2)

(define (reduce source)
    (cog-fc reduct-rule-base source))
