# CERI 7315/8315 Computational Methods for Geodynamics

**Instructor:** Eunseo Choi

**Time and Location:** MWF, 10:20 - 11:15 am.

**Contact:** echoi2\@memphis.edu

## Grades {#grades}

- Topical homeworks: 50 %
- Term project: 30 %
- Quizzes: 20 %

## Office Hours {#office-hours .unnumbered}

- To be arranged individually
- Chatting and meeting via MS Teams preferred

## Goal and Objectives {#course-goal-and-objectives .unnumbered}

This course aims to enable students to understand the basics of the finite element method (FEM), 
a versatile numerical method for solving partial differential equations.

After taking this course, students will be able
to use or modify as necessary the existing community finite element codes (e.g., [CIG codes](https://geodynamics.org/resources/notebooks)) for their geophysical research.

To achieve the goal, we will

1.  review the fundamental governing equations in continuum mechanics,

2.  have under-the-hood understanding of finite element method,

3.  gain hands-on experience with common procedure and useful practices
    in computational research,

4.  use one of the open-source FEM codes, possibly after modifications,
    for their term project.

## References and Online Resources {#references-and-online-resources .unnumbered}

No required textbook but parts of the references listed below will be
used.\

### Reference texts[^1]
[^1]: $^{\dagger}$ means that the UofM Library has an ebook version.
-   Continuum mechanics:

    - Tadmor, E. B., Elliott, R. S., and Miller, R. E. (2012). *Continuum Mechanics and Thermodynamics: From Fundamental Concepts to Governing Equations*. Cambridge University Press,
Cambridge
    - Holzapfel, G. A. (2000). *Nonlinear solid mechanics : a continuum approach for engineering*.
Wiley, Chichester ; New York
    - Malvern, L. E. (1977). *Introduction to the Mechanics of a Continuous Medium*. Prentice-Hall,
Upper Saddle River, New Jersey

-   Fundamental numerical techniques

    - Quarteroni, A., Sacco, R., and Saleri, F. (2000). *Numerical Mathematics*. Springer-Verlag,
New York
    - Zienkiewicz, O. C., Zhu, J. Z., and Taylor, R. L. (2013). *The Finite Element Method: Its Basis
and Fundamentals*. Butterworth-Heinemann, 7th edition
    - Ismail-Zadeh, A. and Tackley, P. (2010). *Computational Methods for Geodynamics*. Cambridge University Press
    - Gerya, T. (2009). *Introduction to Numerical Geodynamic Modelling*. Cambridge University
Press, New York

-   Geodynamics:

    - Turcotte, D. L. and Schubert, G. (2002). *Geodynamics*. Cambridge University Press, New
York, 2nd edition  
    - Schubert, G., Turcotte, D. L., and Olson, P. (2001). *Mantle Convection in the Earth and
Planets*. Cambridge University Press, Cambridge
    - Davies, G. F. (1999). *Dynamic Earth: Plates, Plumes, and Mantle Convection*. Cambridge
University Press, Cambridge  


### Online resources

-   The web sites listed below will help you get familiar with 
the command line-based work environment and other useful tools 
for computational research.

    -   How to work on a Linux(-like) system especially when you are new
        to it:\
        <https://developer.ibm.com/technologies/linux/tutorials/>;\
        search for tutorials with keywords "LPIC-1" and "exam 1"

    -   Lessons on BASH, Python and Git by Software Carpentry:\
        <https://software-carpentry.org/lessons/>

    -   Programming languages (C, Python, etc) and parallel computing
        (OpenMP, MPI, GPU etc)\
        <https://cvw.cac.cornell.edu/topics>

## Term projects {#term-projects .unnumbered}

-   Students carry out a reasonably small but non-trivial project
    relevant to the course's goal and objectives.

-   They should use GitHub to manage their projects and products as
    sharable and reusable resources.

-   A project topic will be decided individually based on students' interests and
    needs.

-   Possible topics:

    -   Consider in a global-scale mantle convection model the effects
        of centrifugal acceleration in addition to the typical
        geocentric gravity

    -   Reproduce and possibly improve a published work on computational
        methods.

    -   Parallelize an existing code with a directive-based approach
        such as OpenMP and OpenACC and assess the performance
        improvement

    -   Introduce recent advances in physics-informed neural networks
        (PINNs)

## Course Outline {#course-outline .unnumbered}

-   Unit 1: A short review of continuum mechanics

-   Unit 2: Numerical toolbox - Principles of numerical mathematics

-   Unit 3: Numerical toolbox - Interpolation: Lagrange polynomial

-   Unit 3: Numerical toolbox - Interpolation: Piecewise Lagrange
    polynomal interpolation in 2D

-   Unit 4: Numerical toolbox - Solving linear equations: Basic
    stability analysis and direct method

-   Unit 4: Numerical toolbox - Solving linear equations: Iterative
    methods and conjugate gradient method

-   Unit 4: Numerical toolbox - Solving linear equations: Krylov
    subspace methods. Solving non-linear systems

-   Unit 5: Numerical toolbox - Approximating function derivatives:
    Finite difference and interpolation-based approach

-   Unit 5: Numerical toolbox - Approximating function derivatives:
    Orthogonal polynomials and weight functions

-   Unit 6: Numerical toolbox - Numerical integration: Gauss and
    Gauss-Lobatto quadrature formula

-   Unit 7: Basic finite element method - Weak forms and variational
    principles

-   Unit 8: Basic finite element method - Walkthrough with the Poisson
    eq. in 1D

-   Unit 9: Basic finite element method - Extension to 2D and 3D


-   Unit 10: Basic finite element method - Solving time-dependent PDEs

-   Unit 11: Selected Topics

    -   Elastic deformation: Static and Dynamic

    -   Basic parallel computing

    -   Introduction to open-source codes: PyLith, ASPECT, FEniCS, or DES3D

