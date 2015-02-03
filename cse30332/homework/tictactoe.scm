;; scheme tictactoe homework
;; name: John F. Lake, Jr.	
;; date: 2 FEB 2015

(load-from-path "/afs/nd.edu/user37/cmc/Public/cse332_sp15/scheme_tictactoe/paradigms_ttt.scm")
(use-modules (ice-9 paradigms_ttt))

;; REPLACE WITH YOUR FUNCTIONS FROM A PREVIOUS HOMEWORK:
;;  greatest
;;  positionof
;;  value

;;MY FUNCTIONS:
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



;; sum*
(define sum*-g
	(lambda (ttup)
   		(cond 
			;; If the tree tup is empty, return 0.
			((null? ttup) 0)	


			;;If the cdr is null, return the value from the car, or the sum of the list that happens to be the car:
			((null? (cdr ttup)) 
				(cond 
					;;If it's a number, simply return the value.
					((number? (car ttup)) (car ttup)) 
					
					;;If it's a list, simply recurse to get its value.
					(else (sum* (car ttup)))
				)
			)


			;;If the cdr is NOT null, return the value from the node plus the value from the cdr. 
			(else
				(cond
					;;If the car is a number, add it to the sum of the cdr. 
					((number? (car ttup)) (+ (car ttup) (sum* (cdr ttup))))

					;;Otherwise, recurse and add the sum of the car to the sum of the cdr.
					(else 
						(+ (sum* (car ttup)) (sum* (cdr ttup)))						
					)
				) 
			)
 		)
	)
)


;; MODIFY this function so that given the game tree 
;; (where the current situation is at the root),
;; it returns the recommendation for the next move
(define nextmove
	(lambda (p gt)
		(cond
			((null? (cdr gt)) 
		)
	)
)
		

;; onegametree is defined in paradigms_ttt
;; be sure to look at that file!

;; what is the current game situation?
(display "Current State:     ")
(display (car (onegametree)))
(display "\n")

;; test of nextmove, where should we go next?
(display "Recommended Move:  ")
(display (nextmove 'x (onegametree)))
(display "\n")

;; correct output:
;;   $ guile tictactoe.scm
;;   Current State:     (x o x o o e e x e)
;;   Recommended Move:  (x o x o o x e x e)

