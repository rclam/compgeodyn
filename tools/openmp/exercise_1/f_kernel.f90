      program kernel

!$    use omp_lib               ! use the OpenMP library

!***  Declare variables
      implicit none
      real*8    :: deltax, dt, x, area
      integer   :: mts, itrial, icount1, icount2, icountr
      integer*8 :: i, n

      write (*,*)

!***  Get the number of Threads (Method 2 with special comment !$)
!$    mts = omp_get_max_threads()
!$    write (*,'(A,I2)') 'Method 2 :: Number of Threads is ', mts
      write (*,*)

      do itrial=1, 4                    ! Loop over different n

        n      = 10_8**(itrial+5)       ! Number of iterations
        deltax = 2._8 / real(n,kind=8)

!*** Start the counter
        call system_clock(icount1, icountr)

!***  Loop over n
!!!!  Add the OpenMP statement here
!!!!  What needs to be private
!$omp parallel do private(...)
        do i=1, n
          x = -1._8 + real(i,kind=8) * deltax
          area = sqrt(1._8 - x*x) * deltax
          if(area < 0.0_8) print*,i,x
        enddo

!*** Stop the counter and calculate the time
        call system_clock(icount2)
        dt = (real(icount2) - real(icount1)) / real(icountr)

!***  Print the output
        write (*,'(a,i12,5x, a,es9.3,a)')  &
          'Number of intervals :', n,      &
          'time = ',               dt, 's'

      enddo

end
