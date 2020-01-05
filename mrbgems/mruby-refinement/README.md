# Implementation the "Refinements" feature for mruby

This is a GEM that can use the "Refinements" feature introduced in Ruby 2.0.

## Important point

- It is not recommended to use this GEM in an environment with less than a few megabytes of RAM.
  The reason is that using the "Refinements" feature consumes extra heap memory.
- Method cache is always disabled within the scope of using the "Refinements" feature.
