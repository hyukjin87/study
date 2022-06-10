const quotes = [
    {
        quote: "Positive anything is better than negative nothing.",
        author: "Elbert Hubbard",
    },
    {
        quote: "Miracles happen to those who believe in them.",
        author: "Bernhard Berenson",
    },
    {
        quote: "One small positive thought can change your whole day.",
        author: "Zig Ziglar",
    },
    {
        quote: "Believe you can and you're halfway there.",
        author: "Teddy Roosevelt",
    },
    {
        quote: "Be positive. Be true. Be kind.",
        author: "Roy T. Bennett",
    },
    {
        quote: "You cannot have a positive life and a negative mind.",
        author: "Joyce Meyer",
    },
    {
        quote: "If you are positive, you'll see opportunities instead of obstacles.",
        author: "Widad Akrawi",
    },
    {
        quote: "Write it on your heart that every day is the best day in the year.",
        author: "Ralph Waldo Emerson",
    },
    {
        quote: "Accentuate the positive, Eliminate the Negative, latch onto the affirmative.",
        author: "Bing Crosby",
    },
    {
        quote: "I will go anywhere as long as it's forward.",
        author: "David Livingston",
    }
]

const quote = document.querySelector("#quote span:first-child")
const author = document.querySelector("#quote span:last-child")

const todaysQuote = quotes[Math.floor(Math.random() * quotes.length)];

quote.innerText = todaysQuote.quote;
author.innerText = todaysQuote.author;