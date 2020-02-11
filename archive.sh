#!/bin/bash -ev

git archive --format=tar.gz -o trigger.tar.gz --prefix=/trigger/ HEAD .

