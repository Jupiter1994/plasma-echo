## Plots and Animations
### Phase mixing
- `plasma_pm.mp4` is a basic phase mixing animation for the plasma case.
- `Gaia_pm_polar_t=100` is a phase mixing animation in polar action-angle coordinates.

### Plots for the full $\delta f$ term
Parameters:
- $n_1=1, n_2=3$
- $t_1=0, t_2=100$
- $A_1=0.1, A_2=0.2$

The relevant files are contained in the folder `deltaf_t1=0_t2=100_n1=1_n2=3`:
- `two_hammers.mp4` shows the full $\delta f$ in $J-\theta$ coordinates, while `two_hammers_polar.mp4` is the same plot in polar coordinates.
- `two_hammers_delta_n_cartesian.png` shows $\delta_n (\theta)$, which is $\delta f$ integrated over $J$ at a certain $\theta$,
while `two_hammers_delta_n_polar.png` shows $\delta_n (\sqrt{J}\cos\theta)$, which is $\delta f$ integrated over $\sqrt{J}\sin\theta$
at a certain $\sqrt{J}\cos\theta$.

### Plots for echo term only ($t_2=100$)
Parameters:
- $n_1=1, n_2=3$
- $t_1=0, t_2=100$
- $A_1=0.1, A_2=0.2$

The relevant files are contained in the folder `echo_only_t2=100_n1=1_n2=3`:
- `gal_echo.mp4` shows the echo part of $\delta f$ in $J-\theta$ coordinates, while `gal_echo_polar.mp4` is the same plot in polar coordinates.
- `gal_echo_delta_n_cartesian.png` shows $\delta_n (\theta)$, which is $\delta f$ integrated over $J$ at a certain $\theta$,
while `gal_echo_delta_n_polar.png` shows $\delta_n (\sqrt{J}\cos\theta)$, which is $\delta f$ integrated over $\sqrt{J}\sin\theta$
at a certain $\sqrt{J}\cos\theta$.

### Plots for echo term only ($t_2=25$)
Parameters:
- $n_1=1, n_2=2$
- $t_1=5, t_2=25$
- $A_1=0.1, A_2=0.2$

The relevant files are contained in the folder `echo_only_t1=5_t2=25_n1=1_n2=2`:
- `gal_echo_t=15_to_55.mp4` shows the echo part of $\delta f$ in $J-\theta$ coordinates,
while `gal_echo_polar_t=15_to_55.mp4` is the same plot in polar coordinates.
- `gal_echo_no_dOmega_dJ.mp4` shows the echo part of $\delta f$ in $J-\theta$ coordinates assuming $\frac{d\Omega}{dJ} = 0$,
while `gal_echo_polar_no_dOmega_dJ.mp4` is the same plot in polar coordinates.
