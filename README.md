# smg-pyleap

This Python package provides Python bindings for the Leap Motion.

It is a submodule of [smglib](https://github.com/sgolodetz/smglib), the open-source Python framework associated with our drone research in the [Cyber-Physical Systems](https://www.cs.ox.ac.uk/activities/cyberphysical/) group at the University of Oxford.

### Installation (as part of smglib)

Note: Please read the [top-level README](https://github.com/sgolodetz/smglib/blob/master/README.md) for smglib before following these instructions.

1. Download and extract the Leap Developer Kit from [here](https://developer.leapmotion.com/releases/?category=orion) (you'll need to register for an account). We used version 3.2.1.

2. Set (at a system level, not within the terminal) the `SMGLIB_LEAP_ROOT_DIR` environment variable to the `LeapSDK` sub-directory within the extracted kit, e.g.

   ```
   C:/Users/<your user>/Downloads/LeapDeveloperKit_3.2.1+45911_win/LeapSDK
   ```

3. Open the terminal, and change to the `<root>/smg-pyleap` directory.

4. Check out the `master` branch.

5. Activate the Conda environment, e.g. `conda activate smglib`.

6. Run `pip install -e .` at the terminal.

### Publications

If you build on this framework for your research, please cite the following paper:
```
@inproceedings{Golodetz2022TR,
author = {Stuart Golodetz and Madhu Vankadari* and Aluna Everitt* and Sangyun Shin* and Andrew Markham and Niki Trigoni},
title = {{Real-Time Hybrid Mapping of Populated Indoor Scenes using a Low-Cost Monocular UAV}},
booktitle = {IEEE/RSJ International Conference on Intelligent Robots and Systems (IROS)},
month = {October},
year = {2022}
}
```

### Acknowledgements

This work was supported by Amazon Web Services via the [Oxford-Singapore Human-Machine Collaboration Programme](https://www.mpls.ox.ac.uk/innovation-and-business-partnerships/human-machine-collaboration/human-machine-collaboration-programme-oxford-research-pillar), and by UKRI as part of the [ACE-OPS](https://gtr.ukri.org/projects?ref=EP%2FS030832%2F1) grant. We would also like to thank [Graham Taylor](https://www.biology.ox.ac.uk/people/professor-graham-taylor) for the use of the Wytham Flight Lab, [Philip Torr](https://eng.ox.ac.uk/people/philip-torr/) for the use of an Asus ZenFone AR, and [Tommaso Cavallari](https://uk.linkedin.com/in/tcavallari) for implementing TangoCapture.
