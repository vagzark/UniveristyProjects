#  Numerical Analysis Project

This is a project created by me and my classmate ιn the context of the course Numerical Analysis.

It is a project with two parts.

For the first part the projessor was asking as to:

- Write code that creates an n×n Hilbert matrix and names this matrix H. Test your code with various values of n to validate that it works correctly.
- Create a vector with elements equal to 1 using the code `b = np.ones((n,1))` and then solve the system `Hx = b` using the factorization mentioned in the previous section.
- Change the value of the first element of b slightly (e.g., add the number \(10^{-15}\) to it) and name the resulting vector bnew. Solve the system \(Hx_{\text{new}} = b_{\text{new}}\) and then calculate the maximum absolute difference using the following line of code: `np.max(np.abs(x - xnew))`. What do you observe? Is the result consistent with what you would expect?
- Create a plot with the values of n on the horizontal axis and the values of the maximum absolute difference on the vertical axis. What conclusions can you draw from this plot regarding the solution of the system \(Hx = b\)?
- You know that the result of \(HH^{-1}\) should be the identity matrix. For various values of \(n\), compute \(HH^{-1}\) (using `np.linalg.inv()` to compute the inverse directly), and then calculate the 2-norm of the difference between the identity matrix (`np.identity(n)`) and the matrix \(HH^{-1}\) that you computed. Finally, create a plot with the values of \(n\) on the horizontal axis and the values of the 2-norm (as defined earlier) on the vertical axis. What do you observe? What does this mean for the process of inverting Hilbert matrices?


The second part is an approximation problem:


It is required to construct a polynomial of degree 4 that best approximates the function:  
<img width="184" alt="Στιγμιότυπο οθόνης 2024-10-08, 12 00 33 πμ" src="https://github.com/user-attachments/assets/1d58a764-0bd5-4846-8b05-c82189eb87bb">

at 50 equally spaced points with t between 0 and 1. In this problem, we assume that ε(t) is a function that extracts normally distributed white noise values. In Python, you can define y as:  
<img width="464" alt="Στιγμιότυπο οθόνης 2024-10-08, 12 01 43 πμ" src="https://github.com/user-attachments/assets/d3d73fe8-8141-4948-b78d-6b2e7cc8bf22">

First, create the vectors t and y that will contain the data/observations. Then, find the polynomial of degree 4 that best approximates the above function for the given observations using the least squares method. Solve the resulting system using LU factorization (method 1) and QR factorization (method 2). Provide the sum of the squared errors resulting from the above approximation for each method and give a plot that contains the data and the curve of the best fit you arrived at.


The project was done by using jupyter notebook and in order to open it you must have an IDE that supports .ipynb files.

