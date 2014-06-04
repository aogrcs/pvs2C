;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;   Author: Gaspard ferey
;; --------------------------------------------------------------------
;;   Draft C translator
;; --------------------------------------------------------------------


(in-package :pvs)


(defvar *definitions-stream* (make-string-output-stream))
(defvar        *main-stream* (make-string-output-stream))


(defun add-definition (str &rest args)
  (apply 'format *definitions-stream* str args)
  (format *definitions-stream* "~%"))

(defun add-main (str &rest args)
  (apply 'format *main-stream* str args)
  (format *main-stream* "~%"))

(defun output-c ()
  (format t (get-output-stream-string *definitions-stream*))
  (format t (get-output-stream-string *main-stream*)))
  

;; This function should return a valid name for a variable used nowhere else
;; A prefixe is given
(defun unused-name (&optional (prefix "_")) (format nil "~a~a" prefix 132) )



(defmethod pvs2C* ((expr number-expr) bindings livevars)
  (declare (ignore bindings livevars))
  (let ((n (number expr)))
    (if (< (abs n) 2147483648) n
      (let ((varname (unused-name "bint")))
        (add-definition "~a = newBigInt(\"~a\");" varname n)
        varname))))







(defparameter *C-primitives* '(== != 1 0 pvsImplies pvsImplies
				   == && && || 
 ! pvsWhen pvsIff pvsAdd pvsSub pvsTimes pvsDiv pvsNumberFieldPred pvsLe pvsLeq pvsGe
 pvsGeq pvsRealPred pvsIntegerPred pvsIntegerPred pvsRationalsPred pvsFloor pvsCeiling
 rem pvsNDiv pvsEven? pvsOdd? pvsCons hd tl isCons null isNull pvsRestrict
 length isMember pvsNth pvsAppend reverse))

(defparameter *pvsC-primitives-map*
  (pairlis *pvs2cl-primitives* *C-primitives*))
  
(defun pvs2C-primitive-op (name)
  (let ((entry (assoc name *pvsC-primitives-map* :test #'same-primitive?)))
    (when entry (cadr entry))))


(defparameter *C-primitives-infix* '(t t nil nil nil nil t t t t
    nil nil nil nil nil nil nil nil nil nil nil nil nil nil nil nil nil
    nil nil nil nil nil nil nil nil nil nil nil nil nil nil nil nil nil))
(defparameter *pvsC-primitives-infix-map*
  (pairlis *pvs2cl-primitives* *C-primitives-infix*))
(defun pvs2C-primitive-infix? (name)
  (let ((entry (assoc name *pvsC-primitives-infix-map* :test #'same-primitive?)))
    (when entry (cdr entry))))

(defparameter *C-primitives-nopar* '(nil nil t t nil nil nil nil nil nil
    t nil nil nil nil nil nil nil nil nil nil nil nil nil nil nil nil
    nil nil nil nil nil nil nil nil nil nil nil nil nil nil nil nil nil))
(defparameter *pvsC-primitives-nopar-map*
  (pairlis *pvs2cl-primitives* *C-primitives-nopar*))
(defun pvs2C-primitive-nopar? (name)
  (let ((entry (assoc name *pvsC-primitives-nopar-map* :test #'same-primitive?)))
    (when entry (cdr entry))))



(defun pvs2C-primitive-app (expr bindings livevars)
  (let* (( o   (operator expr)  )
         (args (pvs2C* (arguments expr) bindings livevars) )
         (prim (pvs2C-primitive-op o)  ))
    (if (pvs2C-primitive-infix? o)
      (add-main (format nil "(~a~a~a)" "~{~a~^ " prim " ~}") args)
      (if (pvs2C-primitive-nopar? o)
        (add-main "~a~{ ~a~}" prim args)
        (add-main "~a(~{~a~^, ~})" prim args)))))









;;
;; Problems :
;;
;; no tuple in ANSI C
;; no bigint (need to write our own int representation in C)
;; 
;; 
;; Solution :
;; Having a function that maps PVS types to C names of C types
;; Having generic functions "mk_*" with * the name of a type
;; Whenever a PVS type is encountered (and created on the run)
;; -> Call "mk_*(param)" to create the C object of the corresponding type
;; 
;; Keep C int type or not?
;; Keep basic built-in C operations  (+, -, ...)
;; 
;; 
;; using rationnals and bigint  (GMP library) to represent PVS types
;; 
;; To write efficient C functions : 
;;  gcd(a: int, b: int) :  int = ...
;; Cgcd(a:Cint, b:Cint) : Cint = ' basically same code using Cfunctions '
;; gcd_is_Cgcd LEMMA Cgcd(a,b) = gcd( int_of_C(a)  ,  int_of_C(b)  )
;;
;;
;;
;;	  (if (C-updateable? (type operator))
;;	      (format nil "(pvsSelect ~a ~a ~a)"
;;		C-op C-arg
;;		(mk-C-funcall C-op
;;				  (list C-arg))))))));;why is there no else case?
;;
;;Should probably be 
;;
;;	  (if (C-updateable? (type operator))
;;	    (format nil "(pvsSelect ~a ~a ~a)" C-op C-arg ???
;;		(mk-C-funcall C-op (list C-arg))
;;    ))))));;why is there no else case?
;;
;;
;;
;;
;;




