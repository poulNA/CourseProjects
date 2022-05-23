# Final Project Grade

Awesome work, everyone! I hope it was a rewarding experience for you all :D

Here are some parts of the final project grade (apart from contract, proposal, and midproject checkin).

If you would like to showcase your work, feel free to clone this repository and host it on your personal git account (github-dev.cs.illinois.edu is being retired soon).

## Development Log

### Grade 

Sophisticated (100%)

Development Log (5 pts)
- [x] >= 4 development logs

### Comments

______________________________________________________________

## Presentation
### Content Grade

Sophisticated (100%)

Final Presentation Content (10 pts)
- [x] A short summary of the goals set for the project and a statement of whether the goals were met.
- [x] Some highlights of the development process (dataset, major design choices, and testing)
- [x] Results of each method
- [x] Concluding thoughts (what was learned and what you would do next)

### Skills Grade

Sophisticated (100%)

Final Presentation Skills (5 pts)
- [x] Roughly equal responsibilities
- [x] Appropriate and understandable visual aids

### Comments

Great visuals, findings, and future plan!

______________________________________________________________

## Written Report
### Grade

Sophisticated (100%)

Written Report (5 pts)
- [x] There are clear descriptions, figures, or tables of each method's output on the full target dataset.
- [x] Projects findings

### Comments

We can make the Markdown a bit prettier too, e.g. reduce image sizes, use code blocks instead of code screenshot. Overall looks great though especially the map and test case drawings.

## README

### Grade

Sophisticated (100%)

Readme (5 pts)
- [x] The linkage and location of all major code, data, results, and deliverable files
- [x] The necessary commands to run the assignment, include instructions for selecting the input dataset and output location
- [x] Instructions on how to reproduce the tests

### Comments

It'd be convenient (at least for me) if there is a concrete command demo for the main application.

______________________________________________________________

## Code

### Goals Grade

Sophisticated (100%)

Code Goals (30 pts)
- [x] All methods listed in goals were successfully developed
- [x] All algorithms can be run on the full target dataset
- [x] All algorithms are thoroughly tested

### Execution Grade

Sophisticated (100%)

Code Execution (5 pts)
- [x] All methods and tests can be run
- [x] Ability to alter or adjust the input data and output location

### Efficiency Grade

Sophisticated (100%)

Code Efficiency (5 pts)
- [x] Code adheres to the expected Big O
- [x] There is no obvious inefficiency
- [x] Complete on target datasets

### Organization Grade

Competent (90%)

Code Organization (5 pts)
- [x] Code is human-readable
- [x] Unnecessary or obsolete code is completely absent

### Comments

Kudos to extensive testing! Especially unit tests around visualization are rare things to see.

The CLI could be improved a bit, e.g. relatable node identifier (maybe coordinate?). Nice that there is a help message.

Running `./final output.png 1 21048` takes \~10 seconds for me.

Code organization is the only main issue I see. Comments in `*.h` explains a lot of user-facing details, but the code in `*.cpp` lacks comments for future developers. We can also organize the code better, e.g. refactor to separate traversal algorithms and graph drawing.

