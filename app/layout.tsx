import type { Metadata, Viewport } from 'next'
import { Inter, Manrope } from 'next/font/google'
import { Analytics } from '@vercel/analytics/next'
import './globals.css'
import { Sidebar } from '@/components/layout/sidebar'
import { TopNav } from '@/components/layout/top-nav'
import { BottomNav } from '@/components/layout/bottom-nav'
import { EmergencyButton } from '@/components/layout/emergency-button'

const inter = Inter({ 
  subsets: ["latin"],
  variable: '--font-inter'
});

const manrope = Manrope({ 
  subsets: ["latin"],
  variable: '--font-manrope'
});

export const metadata: Metadata = {
  title: 'Apothecary Angola | Farmácias e Medicamentos em Luanda',
  description: 'Encontre farmácias, hospitais, postos médicos e medicamentos em Angola. Digitalize receitas e compare preços.',
  generator: 'v0.app',
  keywords: ['farmácia', 'medicamentos', 'angola', 'luanda', 'saúde', 'receitas médicas'],
  icons: {
    icon: [
      {
        url: '/icon-light-32x32.png',
        media: '(prefers-color-scheme: light)',
      },
      {
        url: '/icon-dark-32x32.png',
        media: '(prefers-color-scheme: dark)',
      },
      {
        url: '/icon.svg',
        type: 'image/svg+xml',
      },
    ],
    apple: '/apple-icon.png',
  },
}

export const viewport: Viewport = {
  themeColor: '#003b72',
  width: 'device-width',
  initialScale: 1,
}

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode
}>) {
  return (
    <html lang="pt-AO" className={`${inter.variable} ${manrope.variable}`}>
      <body className="font-sans antialiased bg-background text-foreground">
        <Sidebar />
        <TopNav />
        <main className="md:ml-64 pt-16 pb-24 md:pb-8 min-h-screen">
          {children}
        </main>
        <BottomNav />
        <EmergencyButton />
        {process.env.NODE_ENV === 'production' && <Analytics />}
      </body>
    </html>
  )
}
