#!/usr/bin/env python3
from typing import List
import subprocess


def run_challenge(challenge: int, inputs: List[str], expected: List[str]) -> None:
    print(f"[challenge {challenge:02}]", end=" ")
    res = subprocess.run(
        [f"../build/ex{challenge:02}", *inputs],
        capture_output=True,
        check=True,
        text=True,
    )

    if not expected:
        print(res.stdout)
        return

    assert all(
        out in res.stdout for out in expected
    ), f"Expected output:\n{expected}\nActual output:\n{res.stdout}"

    print("OK")


def main():
    run_challenge(
        challenge=1,
        inputs=[
            "49276d206b696c6c696e6720796f757220627261696e206c69"
            "6b65206120706f69736f6e6f7573206d757368726f6f6d"
        ],
        expected=["SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"],
    )

    run_challenge(
        challenge=2,
        inputs=[
            "1c0111001f010100061a024b53535009181c",
            "686974207468652062756c6c277320657965",
        ],
        expected=["746865206b696420646f6e277420706c6179"],
    )

    run_challenge(
        challenge=3,
        inputs=["1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"],
        expected=["Cooking MC's like a pound of bacon"],
    )

    run_challenge(
        challenge=4, inputs=["../data/4.txt"], expected=["Now that the party is jumping\\n"],
    )

    run_challenge(
        challenge=5,
        inputs=["ICE", "../data/5.txt"],
        expected=[
            "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d"
            "63343c2a26226324272765272a282b2f20430a652e2c652a31"
            "24333a653e2b2027630c692b20283165286326302e27282f"
        ],
    )

    with open("output6.txt", "r") as f:
        output6 = f.read()
    run_challenge(
        challenge=6,
        inputs=["../data/6.txt"],
        expected=["Terminator X: Bring the noise", output6],
    )

    run_challenge(
        challenge=7, inputs=["YELLOW SUBMARINE", "../data/7.txt"], expected=[output6],
    )


if __name__ == "__main__":
    main()
