# References

* Euler angles conversions adapted from [ThreeJS][0]
* Euler angles edge cases handling adapted from [here][1]
* An efficient way to handle all 24 possible Euler angle combintations is
  adapted from [this][2] book (Pages 222-229)
* As reference, we also used the implementation of `Euler to Rotation Matrix`
  conversions from this ROS package [here][3] (implements in Python the
  functions described in the previous [book][2])
* This [video][4] is also a good refresher on Euler angles.
* This [issue][7] explains how to expose views.

---

[0]: <https://github.com/mrdoob/three.js/blob/dev/src/math/Euler.js#L105> (threejs-euler-angles-matrix-conversions)
[1]: <http://eecs.qmul.ac.uk/~gslabaugh/publications/euler.pdf> (matrix-to-euler-angles-conversion-1)
[2]: <http://cas.xav.free.fr/Graphics%20Gems%204%20-%20Paul%20S.%20Heckbert.pdf> (book-graphics-gems-iv)
[3]: <https://github.com/davheld/tf/blob/master/src/tf/transformations.py> (reference-impl-ros-tf)
[4]: <https://youtu.be/3Zjf95Jw2UE> (video-euler-angles-1)
[5]: <https://github.com/davheld/tf/blob/master/src/tf/transformations.py#L1100> (reference-impl-ros-tf-quat-from-euler)
[6]: <https://github.com/davheld/tf/blob/master/src/tf/transformations.py#L1031> (reference-impl-ros-tf-euler-from-matrix)
[7]: <https://github.com/pybind/pybind11/issues/2271> (pybind11-array-view)
