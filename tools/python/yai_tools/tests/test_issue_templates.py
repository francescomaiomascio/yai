import os
import sys
import unittest

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))

from yai_tools.issue.templates import (
    canonical_milestone_title,
    canonical_mp_closure_title,
    canonical_phase_issue_title,
    default_mp_id,
    default_rb_id,
    mp_closure_labels,
    phase_issue_labels,
    pr_phase_labels,
)


class TestIssueTemplates(unittest.TestCase):
    def test_canonical_titles(self):
        self.assertEqual(canonical_milestone_title("contract-baseline-lock", "0.1.0"), "PHASE: contract-baseline-lock@0.1.0")
        self.assertEqual(
            canonical_phase_issue_title("RB-CONTRACT-BASELINE-LOCK", "0.1.0", "Pin Baseline Freeze"),
            "runbook: RB-CONTRACT-BASELINE-LOCK — 0.1.0 Pin Baseline Freeze",
        )
        self.assertEqual(
            canonical_mp_closure_title("MP-CONTRACT-BASELINE-LOCK-0.1.0", "0.1.0"),
            "mp-closure: MP-CONTRACT-BASELINE-LOCK-0.1.0 — 0.1.0 Closure",
        )

    def test_default_ids(self):
        self.assertEqual(default_rb_id("contract-baseline-lock"), "RB-CONTRACT-BASELINE-LOCK")
        self.assertEqual(default_mp_id("contract-baseline-lock"), "MP-CONTRACT-BASELINE-LOCK")
        self.assertEqual(default_mp_id("contract-baseline-lock", "0.1.0"), "MP-CONTRACT-BASELINE-LOCK-0.1.0")

    def test_labels(self):
        self.assertEqual(
            phase_issue_labels("contract-baseline-lock", "0.1.0"),
            ["runbook", "phase:0.1.0", "track:contract-baseline-lock", "governance"],
        )
        self.assertEqual(
            mp_closure_labels("contract-baseline-lock", "0.1.0"),
            ["mp-closure", "phase:0.1.0", "track:contract-baseline-lock", "governance"],
        )
        self.assertEqual(
            pr_phase_labels("contract-baseline-lock", "0.1.0"),
            ["phase:0.1.0", "track:contract-baseline-lock"],
        )


if __name__ == "__main__":
    unittest.main()
