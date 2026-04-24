class StockExpertSystem:

    def __init__(self):
        self.knowledge_base = []

    def ask_questions(self):
        print("\nWelcome to Stock Market Expert System\n")

        risk = input("Enter your risk tolerance (low / medium / high): ").lower()
        trend = input("Enter current market trend (bullish / bearish / sideways): ").lower()
        duration = input("Investment duration (short / medium / long): ").lower()
        capital = input("Capital available (low / medium / high): ").lower()

        self.knowledge_base = {
            "risk": risk,
            "trend": trend,
            "duration": duration,
            "capital": capital
        }

    def inference_engine(self):
        kb = self.knowledge_base

        # RULES

        # Rule 1
        if kb["risk"] == "high" and kb["trend"] == "bullish":
            return "BUY aggressive stocks (small-cap / growth stocks)"

        # Rule 2
        elif kb["risk"] == "low" and kb["trend"] == "bullish":
            return "BUY stable stocks (large-cap / blue-chip)"

        # Rule 3
        elif kb["trend"] == "bearish" and kb["risk"] == "low":
            return "HOLD or invest in defensive stocks (FMCG, Pharma)"

        # Rule 4
        elif kb["trend"] == "bearish" and kb["risk"] == "high":
            return "SELL or short-sell (high risk strategy)"

        # Rule 5
        elif kb["trend"] == "sideways":
            return "HOLD or do intraday trading"

        # Rule 6
        elif kb["duration"] == "long" and kb["capital"] == "high":
            return "Invest in diversified portfolio (Index funds + Blue-chip)"

        # Default rule
        else:
            return "HOLD and observe market"

    def explain_decision(self, decision):
        print("\nExpert System Recommendation:")
        print("->", decision)

    def run(self):
        self.ask_questions()
        decision = self.inference_engine()
        self.explain_decision(decision)


# Run the system
if __name__ == "__main__":
    system = StockExpertSystem()
    system.run()