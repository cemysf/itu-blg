%define SIZE 255	; array size

segment .data
n dd 0	; n = text len.
;m dd 0	; m = pattern len.
i dd 0	; longest prefix in table construction, most matches so far in search
j dd 0	; pattern index in table construction, text index in search
array times SIZE db 0	; prefix table 

;;; registers ;;;
; ebx = i //text len.
; ecx = j //pattern len.
; dh = text len
; dl = pattern len
; esi = address of text
; edi = address of search pattern

segment .text
global kmp
extern strlen

kmp:
	push ebp
	mov ebp, esp
	
	mov esi, [ebp+8]	; esi = address of text
	mov edi, [ebp+12]	; edi = address of search pattern
	
	push edi			; get pattern len. to 
	call strlen
	mov ebx, eax
	add esp, 4 
	
	mov ecx, 0			; i = 0
	mov edx, 2
for:
	cmp ecx,0
	jg if
	cmp
	
if:

	
	cmp ebx,edx
	jz
	
endfor:
	
	
	
	
	pop ebp
	ret
