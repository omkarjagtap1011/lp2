import streamlit as st

# Page config
st.set_page_config(page_title="Railway Chatbot", page_icon="🚆")

# Title
st.title("🚆 Railway Assistant Chatbot")

st.write("Ask me anything about railway services (tickets, refund, luggage, etc.)")

# Chat history
if "chat" not in st.session_state:
    st.session_state.chat = []

# Rule-based chatbot logic
def chatbot_response(user_input):
    user_input = user_input.lower()

    if "hello" in user_input or "hi" in user_input:
        return "Hello! I am your Railway Assistant 🚆. How can I help you?"

    elif "ticket" in user_input or "book" in user_input:
        return "You can book tickets using IRCTC website or mobile app."

    elif "refund" in user_input:
        return "Refund depends on cancellation time. Earlier cancellation = higher refund."

    elif "id proof" in user_input or "documents" in user_input:
        return "Valid ID proofs: Aadhaar, PAN Card, Passport, Voter ID."

    elif "luggage" in user_input:
        return "Limited luggage allowed. Extra baggage may have charges."

    elif "tatkal" in user_input:
        return "Tatkal booking opens 1 day before journey with limited seats."

    elif "platform" in user_input:
        return "Platform number is mentioned on your ticket and station display boards."

    elif "reach" in user_input or "time" in user_input:
        return "Reach station at least 30 minutes before departure."

    elif "food" in user_input:
        return "Food is available at stations and through railway catering services."

    elif "help" in user_input:
        return "Ask me about tickets, refund, luggage rules, Tatkal booking, etc."

    else:
        return "Sorry, I only answer railway-related questions."

# Input box
user_input = st.text_input("💬 Type your question here:")

# Button
if st.button("Send") and user_input:
    response = chatbot_response(user_input)

    # Save chat
    st.session_state.chat.append(("You", user_input))
    st.session_state.chat.append(("Bot", response))

# Display chat history
for sender, msg in st.session_state.chat:
    if sender == "You":
        st.markdown(f"**🧑 You:** {msg}")
    else:
        st.markdown(f"**🚆 Bot:** {msg}")