/** @type {import('tailwindcss').Config} */
module.exports = {
    content: ["./**/*.{razor,cshtml,html}"],
    theme: {
        extend: {
            colors: {
                primaryYellow: "#CCD93E",
                secondaryYellow: "#AEB439",
                ssoDanger: "#FF0000",
            },
        },
    },
    safelist: [
        'bg-primaryYellow',
    ],
    plugins: [],
};
