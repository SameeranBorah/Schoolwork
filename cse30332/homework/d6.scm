;; scheme daily homework 6
;; name: John F. Lake, Jr.  
;; date: 30 Jan 2015

(load-from-path "/afs/nd.edu/user37/cmc/Public/cse332_sp15/scheme_dailies/d6/paradigms_d6.scm")
(use-modules (ice-9 paradigms_d6))

;; greatest
;; return the greatest value in a tup, e.g., (1 3 2) -> 3
(define greatest
	(lambda (tup)
		(cond
			;;If the tup is null, return 0:
			((null? tup) 0)
	
			;;Check and see if the cdr is a number, so you can compare it with the car: 
			((number? (cdr tup)) 

				;;Return the value that's greater:
				(cond
					((> (car tup) (cdr tup)) (car tup))
					(else (cdr tup))	
				)
			)


			;;If it's not a number, see if the car is greater than the other values and recurse on the cdr:
			(else 
				(cond
					((> (car tup) (greatest (cdr tup))) (car tup))
					(else (greatest (cdr tup)))
				)

			)
		)			
	)
) 


;; positionof
;; you may assume that the given tup actually contains n
;; e.g., (positionof 23 (1 52 23 9)) -> 3
(define positionof
	(lambda (n tup)
		(cond
			;;Check and see if n is equal to the car.  If it is, return 1.   
			((eq? (car tup) n) 1)

			;;Otherwise, go to the next item in the list and add1 to the position that will be returned: 
			(else (+ 1 (positionof n (cdr tup))))
		)
	)
) 

;; value
;; given a game state, return the value of that state:
;; 10 if it's a win
;; -10 if it's a loss
;; 0 if it is either a draw or not an ending state
(define value
	(lambda (p gs)
		(cond
			;;If it's a win for you, return 10.
			((win? p gs) 10)

			;;If it's a win for them, return -10. 
			((win? (other p) gs) -10)
			
			;;Return 0 if it's not a win or loss:
			(else 0);
		)	
	)
)

;; tests for greatest
(display (greatest '(1 9 2)))
(display "\n")

(display (greatest '(143 8 31324 24)))
(display "\n")

;; tests for positionof
(display (positionof 23 '(1 52 23 9)))
(display "\n")

(display (positionof 50 '(50 45 1 52 23 9 102)))
(display "\n")

;; tests for value
(display (value 'x '(x o e o x e e e x)))
(display "\n")

(display (value 'x '(o o o x x e e e e)))
(display "\n")

(display (value 'x '(o o e x x e e e e)))
(display "\n")

;; correct output:
;;   $ guile d6.scm
;;   9
;;   31324
;;   3
;;   1
;;   10
;;   -10
;;   0

