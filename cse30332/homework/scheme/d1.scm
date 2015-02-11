;;John F. Lake, Jr. 
;;CSE 30332
;;Scheme Daily 1
;;
;;
;; this is how to load external modules in scheme
;(load-from-path "/home/cmc/teaching/cse332_sp15/svn/assignments/scheme_dailies/d1/public/paradigms_d1.scm")
(load-from-path "/afs/nd.edu/user37/cmc/Public/cse332_sp15/scheme_dailies/d1/paradigms_d1.scm")
(use-modules (ice-9 paradigms_d1))

;; the list q
;; notice it has a ' in front of the list; that tells the interpreter to read
;; the list literally (e.g., as atoms, instead of functions)
(define q '(turkey (gravy) (stuffing potatoes ham) peas))

;; question 1
(display "question 1: ")
(display (atom? (car (cdr (cdr q)))))
(display "\n")
;; output: #f
;; (copy the output you saw here)
;;
;; explanation: Because (stuffing potatoes ham) is a list, rather than an atom,
;; 		it returns false.
;; (use as many lines as necessary, just add more comments)
;;


;; question 2
(display "question 2: ")
(display (lat? (car (cdr (cdr q)))))
(display "\n")
;; output: #t
;;
;;
;; explanation: This makes sense because it should be the opposite of the first
;; 		output.  (stuffing potatoes ham) is a lat, so it's true. 
;;
;;


;; question 3
(display "question 3: ")
(display (cond ((atom? (car q)) (car q)) (else '())))
(display "\n")
;; output: turkey
;;
;;
;; explanation:  This is a conditional.  The car of q is an atom, so the test
;; 		 succeeds and it displays the car of q, which is "turkey". 
;;
;;

